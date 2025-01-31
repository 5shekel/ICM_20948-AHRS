# You need to cut/paste/copy the output data on the serial monitor, 
# then create two separate comma separated value (.csv) file, 
# one each for the magnetometer and accelerometer x,y,z values, and 
# use them for the final calibration steps.

import re
import pandas as pd

# Regular expression pattern for extracting accelerometer and magnetometer data
pattern = re.compile(r"RAW\. Acc \[\s*(-?\d+),\s*(-?\d+),\s*(-?\d+)\s*\],.*Mag \[\s*(-?\d+),\s*(-?\d+),\s*(-?\d+)\s*\]")


# Initialize empty lists to hold the extracted data
acc_data = []
mag_data = []
log_file_path = 'accelerometer_magnetometer.log'

# Read the log file line by line and extract the relevant data
with open(log_file_path, 'r') as f:
    for line in f:
        match = pattern.search(line)
        if match:
            acc_x, acc_y, acc_z, mag_x, mag_y, mag_z = map(int, match.groups())
            acc_data.append([acc_x, acc_y, acc_z])
            mag_data.append([mag_x, mag_y, mag_z])

# Create DataFrames from the lists with no header and no index
acc_df = pd.DataFrame(acc_data, columns=['x', 'y', 'z'])
mag_df = pd.DataFrame(mag_data, columns=['x', 'y', 'z'])


#print how many rows and columns in each dataframe
print(acc_df.shape, mag_df.shape)
# Save the DataFrames to CSV files
acc_csv_path = 'accel_raw.csv'
mag_csv_path = 'mag3_raw.csv'

acc_df.to_csv(acc_csv_path, header=False, index=False)
mag_df.to_csv(mag_csv_path, header=False, index=False)

acc_csv_path, mag_csv_path
