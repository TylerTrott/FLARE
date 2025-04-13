import pandas as pd
import os
import numpy as np
from sklearn.linear_model import LinearRegression

print(f"Current Working Directory of linear_regression.py: {os.getcwd()}")

def get_traffic_files_for_node(location, base_dir="victoriaTrafficData/processed_csvs/"):
    import os
    script_dir = os.path.dirname(os.path.abspath(__file__))
    base_dir = os.path.join(script_dir, base_dir)
    base_dir = os.path.normpath(base_dir)

    matching_files = []
    sanitized_location = location.strip().replace(" ", "").replace("&", "").lower()

    for filename in os.listdir(base_dir):
        if not filename.endswith('.csv'):
            continue
        sanitized_filename = filename.replace(" ", "").replace("&", "").lower()
        # print(f"[DEBUG] Checking file: '{filename}', sanitized as '{sanitized_filename}'")
        if sanitized_filename.startswith(sanitized_location):
            matching_files.append(os.path.join(base_dir, filename))

    if not matching_files:
        raise ValueError(f"No traffic data files found for location: {location}")
    
    print(f"[DEBUG] Matched files: {matching_files}")
    return matching_files

def load_traffic_data(file_path):
    # Read the CSV file
    data = pd.read_csv(file_path)

    # Clean column names: strip spaces
    data.columns = data.columns.str.strip()  # Remove any leading/trailing spaces
    print(f"Columns in the data: {data.columns.tolist()}")

    # Identify if it's a North/South/East/West sheet or a Class sheet
    if 'Leg' in data.columns and 'Movement' in data.iloc[1].values:  # North/South/East/West sheet
        print("Processing North/South/East/West sheet...")
        flattened_data = []
        for col in data.columns:
            if col != 'Start Time':  # Skip Start Time
                leg = data.iloc[0][col]  # Leg is in row 1 (index 0)
                movement = data.iloc[1][col]  # Movement is in row 2 (index 1)
                new_col_name = f"{leg}_{movement}"
                flattened_data.append(new_col_name)
            else:
                flattened_data.append('Start Time')  # Retain Start Time as it is

        data.columns = flattened_data
        print(f"Flattened Columns: {data.columns.tolist()}")

    elif 'Leg' in data.columns and 'Directions' in data.iloc[1].values:  # Class sheet
        print("Processing Class sheet...")
        flattened_data = []
        for col in data.columns:
            if col != 'Start Time':  # Skip Start Time
                leg = data.iloc[0][col]
                direction = data.iloc[1][col]
                movement = data.iloc[2][col]
                new_col_name = f"{leg}_{direction}_{movement}"
                flattened_data.append(new_col_name)
            else:
                flattened_data.append('Start Time')  # Retain Start Time as it is

        data.columns = flattened_data
        print(f"Flattened Columns: {data.columns.tolist()}")

    # Parse 'Start Time' as datetime
    if 'Start Time' not in data.columns:
        print(f"[WARNING] 'Start Time' column missing. Attempting to retrieve from column 1, row 3.")
        potential_start_time = data.iloc[2, 0]
        try:
            pd.to_datetime(potential_start_time)
            data['Start Time'] = pd.to_datetime(data.iloc[2:, 0], errors='coerce')
        except Exception as e:
            print(f"[ERROR] Failed to retrieve 'Start Time': {e}")
            data['Start Time'] = pd.NaT
    else:
        data['Start Time'] = pd.to_datetime(data['Start Time'], errors='coerce')

    # Remove 'Start Time' column after parsing
    if 'Start Time' in data.columns:
        data = data.drop(columns=['Start Time'])

    # Convert non-'Start Time' columns to numeric
    for col in data.columns:
        if col not in ['Leg']:
            data[col] = pd.to_numeric(data[col], errors='coerce')

    numeric_columns = data.select_dtypes(include=['number']).columns.tolist()
    print(f"Numeric Columns: {numeric_columns}")

    if not numeric_columns:
        print(f"[WARNING] No numeric columns found. Adding placeholder.")
        data['Placeholder_Numeric'] = 0
        numeric_columns = ['Placeholder_Numeric']

    target_column = numeric_columns[0]
    y = data[target_column]

    return data, y

def train_model(location, model_weights):
    """
    This function trains a linear regression model using the traffic data for the given location.
    """
    # Get all matching traffic files for the location
    traffic_files = get_traffic_files_for_node(location)
    
    # Load and concatenate all traffic data files
    all_data = []
    for file_path in traffic_files:
        X, y = load_traffic_data(file_path)
        all_data.append(X)
    
    # Concatenate all dataframes into one
    X_all = pd.concat(all_data, ignore_index=True)
    
    # Apply model weights to features
    X_weighted = apply_weights_to_features(X_all, model_weights)
    
    # Train the linear regression model
    model = LinearRegression()
    model.fit(X_weighted, y)
    
    return model

def apply_weights_to_features(X, model_weights):
    """
    This function applies the model weights to the features, subtracting one feature.
    """
    # Ensure model_weights is a numpy array
    model_weights = np.array(model_weights)
    
    # Check if the number of weights matches the number of features
    if len(model_weights) != X.shape[1]:
        raise ValueError("Number of model weights does not match number of features.")
    
    # Subtract one feature (e.g., drop the last column)
    X = X.iloc[:, :-1]  # Drop the last column
    model_weights = model_weights[:-1]  # Drop the last weight
    
    # Apply weights to each feature
    for i, weight in enumerate(model_weights):
        X.iloc[:, i] *= weight  # Element-wise multiplication
    
    return X

def evaluate_model(model, location):
    """
    This function evaluates the trained model. It can return a prediction or a performance metric like R^2.
    """
    # Get all matching traffic files for the location
    traffic_files = get_traffic_files_for_node(location)
    
    # Example: We'll use the first file for evaluation (you can choose another way to evaluate)
    X, y = load_traffic_data(traffic_files[0])  # Use the first file for evaluation
    
    # Use the trained model to make predictions
    y_pred = model.predict(X)
    
    # Calculate R^2 or another metric as needed
    score = model.score(X, y)  # R^2 score
    return score

def run_regression(*args):
    # This function takes the model weights and location, trains the model,
    # and returns the evaluation result.
    
    # Extract model weights and location
    model_weights = args[:-1]  # All arguments except the last one are model weights
    location = args[-1]  # The last argument is the location

    # Train the model
    model = train_model(location, model_weights)
    
    # Evaluate the model
    result = evaluate_model(model, location)
    
    return result

def main():
    # Test locations and their corresponding weights
    test_locations = [
        ("Gonzales Ave & Richardson St", [1, 2, 3]),  # Add actual model weights here
        ("Hillside Ave & Shelbourne St", [1, 2, 3]),
        ("North Dairy Rd & Wordsworth St", [1, 2, 3]),
    ]
    
    # Loop through each test location and attempt to train and evaluate the model
    for location, model_weights in test_locations:
        try:
            print(f"\nRunning regression for location: {location} with weights: {model_weights}")
            
            # Run regression for this location and weights
            result = run_regression(*model_weights, location)
            
            # Output the evaluation result (e.g., R^2 score)
            print(f"Model evaluation result for {location}: {result}")
        except ValueError as e:
            print(f"Error for {location}: {e}")
        except Exception as e:
            print(f"An unexpected error occurred for {location}: {e}")

# Ensure that main() is called directly when running the script
if __name__ == "__main__":
    main()
