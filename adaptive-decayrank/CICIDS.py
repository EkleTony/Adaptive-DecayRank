import pandas as pd
import os

# Define the directory containing your CSV files
directory = '/Users/jaredchristopher/Desktop/_TENTECH/CICIDS2017'
output_filepath = '/Users/jaredchristopher/Desktop/_TENTECH/PythonFormat/'

# List of all your CSV filenames
filenames = [
    'Friday-WorkingHours-Afternoon-DDos.pcap_ISCX.csv',
    'Friday-WorkingHours-Afternoon-PortScan.pcap_ISCX.csv',
    'Friday-WorkingHours-Morning.pcap_ISCX.csv',
    'Monday-WorkingHours.pcap_ISCX.csv',
    'Thursday-WorkingHours-Afternoon-Infilteration.pcap_ISCX.csv',
    'Thursday-WorkingHours-Morning-WebAttacks.pcap_ISCX.csv',
    'Tuesday-WorkingHours.pcap_ISCX.csv',
    'Wednesday-workingHours.pcap_ISCX.csv'
]

# Initialize an empty DataFrame to hold all data
all_data = pd.DataFrame()

# Read and concatenate all CSV files
for filename in filenames:
    filepath = os.path.join(directory, filename)
    df = pd.read_csv(filepath)
    all_data = pd.concat([all_data, df])

# Check the column names in the concatenated DataFrame
print(all_data.columns)

# Adjust based on the actual column names in your data
all_data['timestamp'] = all_data[' Flow Duration']
all_data['sourceport'] = all_data[' Total Fwd Packets']  # Using 'Total Fwd Packets' as a placeholder for sourceport
all_data['targetport'] = all_data[' Destination Port']
all_data['attackflag'] = all_data[' Label'].apply(lambda x: 0 if x.strip() == 'BENIGN' else 1)

# Create the formatted string
all_data['formatted'] = all_data.apply(lambda row: f"{row['timestamp']} {row['sourceport']} {row['targetport']} {row['attackflag']}", axis=1)

# Write the formatted data to a text file
output_filepath = os.path.join(output_filepath, 'formatted_CICIDS.txt')
with open(output_filepath, 'w') as f:
    for line in all_data['formatted']:
        f.write(line + '\n')

print(f"Formatted data has been written to {output_filepath}")
