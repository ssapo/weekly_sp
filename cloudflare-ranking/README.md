# Cloudflare Ranking API

This is a free-tier friendly ranking backend for the 2048 page.

## What it does

- `GET /leaderboard?limit=10`
- `POST /scores`
- `GET /health`

## Setup

1. Create a Cloudflare D1 database.
2. Put the real D1 database id into `wrangler.toml`.
3. Run the schema:

```bash
npx wrangler d1 execute weekly-sp-ranking --file=./schema.sql
```

4. Deploy the worker:

```bash
npx wrangler deploy
```

5. Set the worker URL in the 2048 frontend by defining:

```html
<script>
  window.__RANKING_API_BASE__ = "https://your-worker-name.your-subdomain.workers.dev";
</script>
```

Add that before the main game script in `docs/2048-v2/index.html` and `2048/index.html`.

## Score payload

```json
{
  "playerId": "player-abc",
  "displayName": "ssapo",
  "score": 4096
}
```

For now the frontend uses a per-browser local id so the feature can work without paid auth or OAuth setup.
