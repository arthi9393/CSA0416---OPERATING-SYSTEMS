#!/usr/bin/env bash
# B2 - run step by step (not all at once) and save each output with | tee B2_<step>.txt
docker build -t result-portal .
docker images result-portal                      # record SIZE
docker run -d --name portal -p 8000:8000 result-portal
docker ps; curl -s localhost:8000; curl -s localhost:8000/health
docker exec portal whoami                        # expected: portal
docker history result-portal                     # inspect layers
docker rm -f portal

# Resource limits and their effect
docker run -d --name limited --cpus 0.5 --memory 128m -p 8000:8000 result-portal
docker stats --no-stream limited                 # note MEM LIMIT and CPU %
docker rm -f limited

# Compose with volume
docker compose up -d --build
curl -s localhost:8000/visits; curl -s localhost:8000/visits
docker compose restart db; curl -s localhost:8000/visits   # count keeps growing -> volume works
docker compose down            # keep volume;  'docker compose down -v' would delete the data
docker stats --no-stream

# Size comparison (alternative concept)
time docker build -t portal-slim -f Dockerfile .
time docker build -t portal-multistage -f Dockerfile.multistage .
time docker build -t portal-ubuntu -f Dockerfile.ubuntu .
docker images | grep portal-
