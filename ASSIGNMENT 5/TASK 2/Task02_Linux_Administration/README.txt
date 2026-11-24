Run: bash log_summary.sh; bash disk_alert.sh /
Example cron (hourly): 0 * * * * /opt/scripts/log_summary.sh >> /var/log/portal-summary.log 2>&1
Service and Nginx files are templates; install only after adapting paths and users.