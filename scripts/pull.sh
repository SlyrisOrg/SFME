#!/bin/bash

git pull
git submodule foreach --recursive git checkout master
git submodule foreach --recursive git pull
