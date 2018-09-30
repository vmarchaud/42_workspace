provider "google" {
  credentials = "${file("account.json")}"
  project     = "test-42"
  region      = "europe-west2"
}

/** Redis **/
resource "google_redis_instance" "redis" {
  name = "wordpress-redis-instance"
  memory_size_gb = 1
}

/** Network **/
resource "google_compute_network" "default" {
  name = "wordpress-network"
  auto_create_subnetworks = "true"
}

/** SQL **/
resource "google_sql_database_instance" "master" {
  name = "wordpress-sql-instance"

  settings {
    tier = "D0"
  }
}

resource "google_sql_database" "wordpress" {
  name      = "wordpress-db"
  instance  = "${google_sql_database_instance.master.name}"
  charset   = "latin1"
  collation = "latin1_swedish_ci"
}

/** LB **/
resource "google_compute_target_http_proxy" "default" {
  name        = "test-proxy"
  url_map     = "${google_compute_url_map.default.self_link}"
}

resource "google_compute_url_map" "default" {
  name        = "url-map"

  default_service = "${google_compute_backend_service.default.self_link}"
}

resource "google_compute_backend_service" "default" {
  name        = "my-backend"
  port_name   = "http"
  protocol    = "HTTP"
  timeout_sec = 10
  enable_cdn  = false

  backend {
    group = "${google_compute_region_instance_group_manager.default.instance_group}"
  }

  health_checks = ["${google_compute_health_check.default.self_link}"]
}

/** CDN **/


/** Autoscaling **/
resource "google_compute_instance_template" "default" {
  name           = "wordpress-web"
  machine_type   = "n1-standard-1"
  can_ip_forward = false

  disk {
    source_image = "debian-cloud/debian-8"
  }

  network_interface {
    network = "${google_compute_network.default.self_link}"
  }
}

resource "google_compute_target_pool" "default" {
  name = "wordpress-target-pool"
}

resource "google_compute_health_check" "default" {
  name                = "autohealing-health-check"
  check_interval_sec  = 5
  timeout_sec         = 5
  healthy_threshold   = 2
  unhealthy_threshold = 10

  http_health_check {
    request_path = "/healthz"
    port         = "80"
  }
}

resource "google_compute_region_instance_group_manager" "default" {
  name = "wordpress-igm"

  base_instance_name         = "wordpress"
  instance_template          = "${google_compute_instance_template.default.self_link}"
  region                     = "europe-west2"

  target_pools = ["${google_compute_target_pool.default.self_link}"]
  target_size  = 2

  update_strategy = "ROLLING_UPDATE"
  rolling_update_policy {
    type = "PROACTIVE"
    minimal_action = "REPLACE"
    max_surge_percent = 20
    max_unavailable_fixed = 2
    min_ready_sec = 50
  }

  auto_healing_policies {
    health_check      = "${google_compute_health_check.default.self_link}"
    initial_delay_sec = 300
  }
}

resource "google_compute_autoscaler" "default" {
  name   = "auto-scaler"
  target = "${google_compute_region_instance_group_manager.default.self_link}"

  autoscaling_policy {
    max_replicas    = 5
    min_replicas    = 1
    cooldown_period = 60

    cpu_utilization {
      target = 0.5
    }
  }
}
