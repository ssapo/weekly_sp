export default {
  async fetch(request, env) {
    const url = new URL(request.url);

    if (request.method === "OPTIONS") {
      return new Response(null, {
        status: 204,
        headers: corsHeaders()
      });
    }

    try {
      if (url.pathname === "/health") {
        return json({ ok: true });
      }

      if (url.pathname === "/leaderboard" && request.method === "GET") {
        const limit = Math.min(Number(url.searchParams.get("limit") || 10), 50);
        const { results } = await env.DB.prepare(
          "SELECT display_name AS displayName, best_score AS bestScore, updated_at AS updatedAt FROM scores ORDER BY best_score DESC, updated_at ASC LIMIT ?"
        ).bind(limit).all();

        return json({ entries: results || [] });
      }

      if (url.pathname === "/scores" && request.method === "POST") {
        const body = await request.json();
        const playerId = String(body.playerId || "").trim();
        const displayName = String(body.displayName || "").trim();
        const score = Number(body.score || 0);

        if (!playerId || !displayName || !Number.isFinite(score)) {
          return json({ error: "Invalid payload" }, 400);
        }

        if (displayName.length < 2 || displayName.length > 16) {
          return json({ error: "Display name must be 2-16 chars" }, 400);
        }

        const now = new Date().toISOString();
        await env.DB.prepare(
          `INSERT INTO scores (player_id, display_name, best_score, updated_at)
           VALUES (?, ?, ?, ?)
           ON CONFLICT(player_id) DO UPDATE SET
             display_name = excluded.display_name,
             best_score = CASE
               WHEN excluded.best_score > scores.best_score THEN excluded.best_score
               ELSE scores.best_score
             END,
             updated_at = CASE
               WHEN excluded.best_score >= scores.best_score THEN excluded.updated_at
               ELSE scores.updated_at
             END`
        ).bind(playerId, displayName, Math.floor(score), now).run();

        return json({ ok: true });
      }

      return json({ error: "Not found" }, 404);
    } catch (error) {
      return json({ error: "Server error", detail: String(error) }, 500);
    }
  }
};

function json(data, status = 200) {
  return new Response(JSON.stringify(data), {
    status,
    headers: {
      "Content-Type": "application/json; charset=utf-8",
      ...corsHeaders()
    }
  });
}

function corsHeaders() {
  return {
    "Access-Control-Allow-Origin": "*",
    "Access-Control-Allow-Methods": "GET, POST, OPTIONS",
    "Access-Control-Allow-Headers": "Content-Type"
  };
}

