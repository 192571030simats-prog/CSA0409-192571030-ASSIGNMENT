Build: docker build -t result-portal .
Run: docker run --rm -p 8000:8000 --cpus=0.5 --memory=512m result-portal
Compose: docker compose up --build -d
Inspect: docker history result-portal; docker stats
Use secrets and strong credentials for any non-demo deployment.