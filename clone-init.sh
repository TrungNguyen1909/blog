#!/bin/sh
git submodule init
git submodule update
git worktree add public origin/gh-pages
cd public
git checkout gh-pages

