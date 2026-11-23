#!/usr/bin/env bash
# B3 - run step by step; record outputs in B3_results_table (see report). Tools: ab (apache2-utils), docker, minikube/kind, kubectl.
URL=http://localhost:8000/health

# B3.1/B3.2 (a) BARE METAL: run directly on Linux
python3 -m venv venv && . venv/bin/activate && pip install -r requirements.txt
/usr/bin/time -v gunicorn --bind 0.0.0.0:8000 app:app &   # note start-up, then:
sleep 2; curl -s $URL
ps -o rss,cmd -C gunicorn                          # RSS in KB = memory used
ab -n 20000 -c 100 $URL | grep -E "Requests per second|Time per request|Failed"
pkill gunicorn

# (b) CONTAINER
start=$(date +%s.%N); docker run -d --name c1 -p 8000:8000 result-portal
until curl -sf $URL >/dev/null; do sleep 0.1; done
echo "container start-up: $(echo "$(date +%s.%N) - $start" | bc) s"
docker stats --no-stream c1; docker images result-portal
ab -n 20000 -c 100 $URL | grep -E "Requests per second|Time per request|Failed"
docker rm -f c1

# (c) VIRTUAL MACHINE: inside a VirtualBox/KVM Ubuntu guest (port-forward host 8001 -> guest 8000)
#   in guest:  repeat bare-metal steps; in host: ab -n 20000 -c 100 http://localhost:8001/health
#   Measure: boot time of VM (stopwatch / systemd-analyze), 'free -m' in the guest, VM disk file size (ls -lh *.vdi / *.qcow2)

# B3.3 KUBERNETES (minikube shown; kind is similar)
minikube start --cpus 4 --memory 4096
eval $(minikube docker-env) && docker build -t simats/result-portal:1.0 .
kubectl apply -f deployment.yaml
kubectl get pods
kubectl describe pod $(kubectl get pods -o name | head -1) | grep -A6 -E "Limits|Requests"
kubectl delete pod $(kubectl get pods -o name | head -1)   # then:
kubectl get pods -w                                        # a new pod appears automatically
minikube addons enable metrics-server
kubectl apply -f hpa.yaml
kubectl scale deployment result-portal --replicas=6        # manual scale to 6
kubectl get pods
# load while watching autoscaler (second terminal: kubectl get hpa -w)
kubectl port-forward svc/result-portal 8080:80 &
ab -n 100000 -c 200 http://localhost:8080/health
