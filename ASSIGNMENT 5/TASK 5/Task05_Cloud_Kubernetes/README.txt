Apply: kubectl apply -f deployment.yaml
Inspect: kubectl get deployments,pods,services
Scale: kubectl scale deployment/result-portal --replicas=6
HPA: kubectl apply -f hpa.yaml
The image name must be replaced with an image built and pushed to a registry accessible by the cluster.