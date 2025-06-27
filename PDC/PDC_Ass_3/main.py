# import matplotlib.pyplot as plt

# # CPU Execution Time Breakdown
# cpu_labels = ["convertImageToFloat", "applyEdgeDetection", "saveOutputImage"]
# cpu_times = [2832.865, 1477.400, 6015.155]  # Derived from cumulative times

# # Group minor OpenCL times into "Other Operations"
# ocl_labels_grouped = ["convertImageToFloat", "OpenCL Operations", "saveOutputImage"]
# ocl_times_grouped = [1138.002, sum([7.187, 5.530, 37.641]), 3426.395]  # Summing minor times

# fig, ax = plt.subplots(1, 2, figsize=(12, 6))

# # CPU Pie Chart
# ax[0].pie(cpu_times, labels=cpu_labels, autopct='%1.1f%%', colors=['skyblue', 'lightgreen', 'lightcoral'])
# ax[0].set_title("CPU Execution Time Breakdown")

# # OpenCL Pie Chart (Grouped)
# ax[1].pie(ocl_times_grouped, labels=ocl_labels_grouped, autopct='%1.1f%%', colors=['gold', 'gray', 'lightcoral'])
# ax[1].set_title("OpenCL Execution Time Breakdown (Grouped)")

# plt.tight_layout()
# plt.show()


import matplotlib.pyplot as plt
import pandas as pd

# Data
data = {
    "Test Type": ["Number of Points"] * 7 + ["Resolution"] * 7,
    "Points": [1000, 2000, 4000, 8000, 16000, 32000, 64000] * 2,
    "OpenMP Time (s)": [0.061331, 0.086058, 0.068045, 0.088674, 0.131035, 0.114877, 0.076410,
                         0.008239, 0.010569, 0.063936, 0.228713, 1.278147, 5.747606, 37.997584],
    "Serial Time (s)": [0.195000, 0.162000, 0.135000, 0.109000, 0.192000, 0.159000, 0.163000,
                        0.006000, 0.019000, 0.055000, 0.441000, 2.032000, 9.251000, 61.935000]
}

df = pd.DataFrame(data)

# Plot
fig, ax = plt.subplots(1, 2, figsize=(12, 5))

# Number of Points Test
df_points = df[df["Test Type"] == "Number of Points"]
ax[0].plot(df_points["Points"], df_points["OpenMP Time (s)"], marker='o', label="OpenMP")
ax[0].plot(df_points["Points"], df_points["Serial Time (s)"], marker='s', label="Serial")
ax[0].set_xscale('log')
ax[0].set_yscale('log')
ax[0].set_title("Performance Comparison: Number of Points")
ax[0].set_xlabel("Number of Points (log scale)")
ax[0].set_ylabel("Time (seconds, log scale)")
ax[0].legend()
ax[0].grid(True, which="both")

# Resolution Test
df_res = df[df["Test Type"] == "Resolution"]
ax[1].plot(df_res["Points"], df_res["OpenMP Time (s)"], marker='o', label="OpenMP")
ax[1].plot(df_res["Points"], df_res["Serial Time (s)"], marker='s', label="Serial")
ax[1].set_xscale('log')
ax[1].set_yscale('log')
ax[1].set_title("Performance Comparison: Resolution")
ax[1].set_xlabel("Resolution (log scale)")
ax[1].set_ylabel("Time (seconds, log scale)")
ax[1].legend()
ax[1].grid(True, which="both")

plt.tight_layout()
plt.show()
