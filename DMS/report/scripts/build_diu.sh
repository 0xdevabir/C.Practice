#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"
WORKDIR=$(mktemp -d)
trap 'rm -rf "$WORKDIR"' EXIT

python3 scripts/palette.py \
  --title "Distribution Management System" \
  --type academic \
  --author "CSE114 Lab Project Team" \
  --date "August 2026" \
  --accent "#2A4A6B" \
  --out "$WORKDIR/tokens.json" >/dev/null

python3 - <<PY
import json
from pathlib import Path
p = Path("$WORKDIR/tokens.json")
t = json.loads(p.read_text())
t["subtitle"] = "MINI LAB PROJECT REPORT - CSE114"
p.write_text(json.dumps(t, indent=2))
PY

python3 scripts/render_body.py \
  --tokens "$WORKDIR/tokens.json" \
  --content content.json \
  --out "$WORKDIR/body.pdf"

# Cover = DIU lab report cover PNG as full A4 page
python3 - <<PY
from pathlib import Path
from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import A4
from reportlab.lib.utils import ImageReader
cover_png = Path("DIU_Lab_Report_Cover.png")
out = Path("$WORKDIR/cover.pdf")
c = canvas.Canvas(str(out), pagesize=A4)
w, h = A4
c.drawImage(ImageReader(str(cover_png)), 0, 0, width=w, height=h, preserveAspectRatio=True, anchor="c")
c.save()
print("cover pdf ok")
PY

python3 scripts/merge.py \
  --cover "$WORKDIR/cover.pdf" \
  --body "$WORKDIR/body.pdf" \
  --out DMS_Project_Report.pdf \
  --title "Distribution Management System"
