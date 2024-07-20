
#Task 1 accesing process directory and print the information
total_processors=$(grep -c "^processor" /proc/cpuinfo)
physical_cores=$(grep -c "^core id" /proc/cpuinfo)
hyperthreading_enabled=$(grep -q "^siblings" /proc/cpuinfo && echo "Yes" || echo "No")
total_cores_with_hyperthreading=$(grep "^siblings" /proc/cpuinfo | head -n 1 | awk '{print $3}')
processor_model=$(grep -m 1 "model name" /proc/cpuinfo | cut -d':' -f2 | sed 's/^ *//')


echo "Total Number of Processors: $total_processors"
echo "Total Number of Physical Cores: $physical_cores"
echo "Is Hyperthreading Enabled: $hyperthreading_enabled"
echo "Total Number of Cores with Hyperthreading: $total_cores_with_hyperthreading"
echo "Processor Model: $processor_model"

echo "Total Number of Processors: $total_processors" > CPU_info.txt
echo "Total Number of Physical Cores: $physical_cores" >> CPU_info.txt
echo "Is Hyperthreading Enabled: $hyperthreading_enabled" >> CPU_info.txt
echo "Total Number of Cores with Hyperthreading: $total_cores_with_hyperthreading" >> CPU_info.txt
echo "Processor Model: $processor_model" >> CPU_info.txt

echo "CPU information has been saved in CPU_info.txt"
