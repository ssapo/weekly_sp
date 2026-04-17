CREATE TABLE IF NOT EXISTS scores (
  player_id TEXT PRIMARY KEY,
  display_name TEXT NOT NULL,
  best_score INTEGER NOT NULL DEFAULT 0,
  updated_at TEXT NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_scores_best_score
ON scores(best_score DESC, updated_at ASC);

