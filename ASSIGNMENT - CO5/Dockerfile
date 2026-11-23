# Container image for the campus result-portal web service (a small Flask app).
FROM python:3.12-slim
# TODO 1 (done): working directory inside the image
WORKDIR /app
# Install the dependencies first so that this layer is cached between builds.
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt
# TODO 2 (done): copy the application source and run as a non-root user named portal
COPY app.py .
RUN useradd --create-home --shell /usr/sbin/nologin portal && chown -R portal:portal /app
USER portal
# TODO 3 (done): document the port and start gunicorn on 0.0.0.0:8000 using the app object in app.py
EXPOSE 8000
CMD ["gunicorn", "--bind", "0.0.0.0:8000", "app:app"]
