#!/usr/bin/env python3
import math

students = 150_000
window_hours = 2
requests_per_student = 4
measured_rps_per_instance = 25.0  # Replace with measured benchmark result
safety_factor = 1.5

total_requests = students * requests_per_student
window_seconds = window_hours * 60 * 60
required_rps = total_requests / window_seconds
instances = math.ceil(required_rps * safety_factor / measured_rps_per_instance)

print(f"Students: {students:,}")
print(f"Window: {window_hours} hours")
print(f"Assumed requests per student: {requests_per_student}")
print(f"Average required throughput: {required_rps:.2f} requests/second")
print(f"Safety factor: {safety_factor:.2f}")
print(f"Assumed measured capacity per instance: {measured_rps_per_instance:.2f} requests/second")
print(f"Estimated instances: {instances}")
print("IMPORTANT: Replace assumptions with measured load-test data.")
