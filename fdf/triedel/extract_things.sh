#!/bin/sh
SRC="$HOME/Downloads"
DEST="./things"

mkdir -p "$DEST"

find "$SRC" -type f -iname '*.zip' | while read -r z
do
  echo "Extracting from $z"
  unzip -l "$z" | awk '{ print $NF }' | grep -i '.stl$' | while read -r f
  do
    echo "File $f"
    unzip -p "$z" "$f" > "$DEST"/"$(basename "$f")"
  done
done

./fdf m things/*
