import os
import pandas as pd
import re
import shutil

# Path to the directory containing the Excel files
base_dir = os.path.dirname(__file__)  # path to directory where script lives
directory_path = os.path.join(base_dir, '2025 TMC Collection Program')

def clear_processed_csvs(output_dir):
    # If the directory exists, clear its contents
    if os.path.exists(output_dir):
        shutil.rmtree(output_dir)
    # Recreate the directory
    os.makedirs(output_dir, exist_ok=True)

def process_spreadsheet(file_path, output_dir):
    try:
        # Load the Excel file
        xls = pd.ExcelFile(file_path)
        dfs = {}  # Dictionary to hold DataFrames
        location = None  # Default value for location

        # Read the Summary sheet (if present)
        if 'Summary' in xls.sheet_names:
            summary_df = pd.read_excel(xls, sheet_name='Summary')
            dfs['summary'] = summary_df

            # Retrieve intersection location
            if len(summary_df.columns) > 1:
                location = summary_df.columns.tolist()[1]

        # Process traffic direction sheets (Northbound, Southbound, etc.)
        for direction in ['Northbound', 'Southbound', 'Westbound', 'Eastbound']:
            if direction in xls.sheet_names:
                direction_df = pd.read_excel(xls, sheet_name=direction, header=1)  # Read with second row as header
                direction_df = direction_df.dropna(how='all')  # Drop rows that are completely empty

                # Ensure 'Start Time' is datetime and handle missing values
                if 'Start Time' in direction_df.columns:
                    direction_df['Start Time'] = pd.to_datetime(direction_df['Start Time'], errors='coerce')
                direction_df = direction_df.fillna(0)  # Fill NaN values with 0

                dfs[direction.lower()] = direction_df

        # Process sheets with 'Class' in the title
        for sheet_name in xls.sheet_names:
            if 'class' in sheet_name:
                class_df = pd.read_excel(xls, sheet_name=sheet_name, header=2)  # Read with third row as header
                class_df = class_df.dropna(how='all')  # Drop rows that are completely empty

                # Ensure 'Start Time' is datetime and handle missing values
                if 'Start Time' in class_df.columns:
                    class_df['Start Time'] = pd.to_datetime(class_df['Start Time'], errors='coerce')
                class_df = class_df.fillna(0)  # Fill NaN values with 0

                dfs[sheet_name.lower().replace(" ", "_")] = class_df

        # === Export all dfs to CSV ===
        if not location:
            location = os.path.splitext(os.path.basename(file_path))[0]  # Fallback to file name if location is not found

        # Sanitize location name: Remove any 'id-' or digits
        sanitized_location = re.sub(r'^\d+\s*-\s*', '', location)  # Remove leading ID if present
        sanitized_location = sanitized_location.replace(" ", "").replace("&", "")  # Remove spaces & ampersands

        # Loop over all dataframes to save them as CSV
        for name, df in dfs.items():
            if df.empty:
                continue

            sanitized_name = name.replace(" ", "").replace("&", "")
            output_path = os.path.join(output_dir, f"{sanitized_location}_{sanitized_name}.csv")
            df.to_csv(output_path, index=False)
            # print(f"Saved: {output_path}")

    except Exception as e:
        print(f"Failed to process {file_path}: {e}")
        
# Loop through all files in the directory and process them
def main():
    try:
        output_dir = os.path.join(base_dir, 'processed_csvs')
        
        # Clear the output directory before processing new files
        clear_processed_csvs(output_dir)

        for file_name in os.listdir(directory_path):
            file_path = os.path.join(directory_path, file_name)
            # Check if the file is an Excel file
            if file_name.endswith('.xlsx'):
                process_spreadsheet(file_path, output_dir)  # Correctly passing both arguments
             #   print(f"Processed {file_name} and saved to {output_dir}")
        
    except Exception as e:
        # Handle exception: Print the error message
        print(f"An error occurred in the main execution: {e}")

# Ensure that main() is called directly when running the script
if __name__ == "__main__":
    main()
