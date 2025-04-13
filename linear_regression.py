import pandas as pd
import numpy as np
from sklearn.linear_model import LinearRegression

def run_regression(*args):
    if len(args) < 2:
        raise ValueError("Insufficient arguments passed to run_regression.")

    weights = args[:-1]
    location = args[-1]

    print(f"[PY] Received weights: {weights}")
    print(f"[PY] Location: {location}")

    df = pd.read_csv("test_traffic_data.csv")

    # Convert categorical columns
    df['day_of_week'] = df['day_of_week'].map({
        'Mon': 0, 'Tue': 1, 'Wed': 2, 'Thu': 3, 'Fri': 4, 'Sat': 5, 'Sun': 6
    })
    # Map weather to numeric, using 'Clear' as default for unmapped or missing values
    weather_map = {'Clear': 0, 'Cloudy': 1, 'Rain': 2}
    df['weather'] = df['weather'].map(weather_map)
    df['weather'] = df['weather'].map(weather_map).fillna(weather_map['Clear'])

    features = ['hour', 'minute', 'day_of_week', 'weather']
    X = df[features].to_numpy()

    # Check for NaNs in features
    print(f"[DEBUG] Feature matrix (before bias):\n{X}")
    print(f"[DEBUG] NaNs in feature matrix: {np.isnan(X).any()}")

    # Add bias
    X = np.hstack((np.ones((X.shape[0], 1)), X))  # Bias term

    # Check for NaNs in weights
    print(f"[DEBUG] NaNs in weights: {any([w is None or np.isnan(w) for w in weights])}")

    if len(weights) != X.shape[1]:
        raise ValueError(f"Number of model weights ({len(weights)}) does not match number of features ({X.shape[1]}).")

    y_pred = np.dot(X, np.array(weights))

    # Final check
    print(f"[DEBUG] Predictions (first 10): {y_pred[:10]}")
    print(f"[DEBUG] NaNs in predictions: {np.isnan(y_pred).any()}")

    avg_prediction = float(np.nanmean(y_pred))  # Use nanmean just in case
    print(f"[PY] Returning average predicted traffic: {avg_prediction:.2f}")
    return avg_prediction