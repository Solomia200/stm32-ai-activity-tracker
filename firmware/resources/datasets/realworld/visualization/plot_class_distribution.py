"""Script to load dataset and plot class distribution."""

from pathlib import Path
import numpy as np
import matplotlib.pyplot as plt


def plot_class_distribution(
    dataset_path: str,
    output_path: str,
    title: str = "Class Distribution",
    figsize: tuple = (10, 6),
    dpi: int = 300,
    class_names: dict = None
) -> Path:
    """
    Load dataset from numpy array and plot class distribution.
    
    Args:
        dataset_path: Path to the numpy dataset file (.npz or directory with .npy files)
        output_path: Path where the plot will be saved
        title: Title for the plot
        figsize: Figure size (width, height)
        dpi: Resolution in dots per inch
        class_names: Dictionary mapping class IDs to names (optional)
        
    Returns:
        Path object pointing to the saved plot
    """
    # Default class names
    if class_names is None:
        class_names = {
            0: "walking",
            1: "running",
            2: "climbing down",
            3: "climbing up",
            4: "resting"
        }
    dataset_path = Path(dataset_path)
    output_path = Path(output_path)
    
    if not dataset_path.exists():
        raise FileNotFoundError(f"Dataset not found: {dataset_path}")
    
    output_path.parent.mkdir(parents=True, exist_ok=True)
    
    print(f"Loading dataset from: {dataset_path}")
    
    # Load data based on file type
    if dataset_path.is_file():
        if dataset_path.suffix == '.npz':
            # Load .npz file
            data = np.load(str(dataset_path))
            if 'y' in data:
                labels = data['y']
            elif 'labels' in data:
                labels = data['labels']
            else:
                # Try to get the first array that looks like labels
                possible_keys = [k for k in data.keys()]
                print(f"Available keys in .npz: {possible_keys}")
                labels = data[possible_keys[-1]]  # Assume last key is labels
        elif dataset_path.suffix == '.npy':
            # Load .npy file - assume it contains labels
            labels = np.load(str(dataset_path))
        else:
            raise ValueError(f"Unsupported file type: {dataset_path.suffix}")
    else:
        # Try to load from directory (look for y.npy or labels.npy)
        label_files = ['y.npy', 'labels.npy', 'y_train.npy', 'train_labels.npy']
        labels = None
        for label_file in label_files:
            label_path = dataset_path / label_file
            if label_path.exists():
                labels = np.load(str(label_path))
                print(f"Loaded labels from: {label_file}")
                break
        
        if labels is None:
            raise FileNotFoundError(f"No label file found in directory: {dataset_path}")
    
    # Flatten if necessary
    if labels.ndim > 1:
        labels = labels.flatten()
    
    # Get unique classes and counts
    unique_classes, counts = np.unique(labels, return_counts=True)
    
    print(f"\nClass distribution:")
    for cls, count in zip(unique_classes, counts):
        percentage = (count / len(labels)) * 100
        class_name = class_names.get(cls, f"Class {cls}")
        print(f"  {class_name} ({cls}): {count:6d} samples ({percentage:5.2f}%)")
    print(f"Total samples: {len(labels)}")
    
    # Create plot
    fig, ax = plt.subplots(figsize=figsize)
    
    # Create bar plot
    bars = ax.bar(unique_classes, counts, color='steelblue', edgecolor='black', linewidth=1.5)
    
    # Add value labels on bars
    for bar, count in zip(bars, counts):
        height = bar.get_height()
        percentage = (count / len(labels)) * 100
        ax.text(bar.get_x() + bar.get_width()/2., height,
                f'{count}\n({percentage:.1f}%)',
                ha='center', va='bottom', fontsize=10, fontweight='bold')
    # Styling
    ax.set_xlabel('Activity', fontsize=12, fontweight='bold')
    ax.set_ylabel('Number of Samples', fontsize=12, fontweight='bold')
    ax.set_title(title, fontsize=14, fontweight='bold', pad=20)
    ax.set_xticks(unique_classes)
    ax.set_xticklabels([class_names.get(cls, f'Class {cls}').capitalize() 
                        for cls in unique_classes], rotation=45, ha='right')
    ax.grid(axis='y', alpha=0.3, linestyle='--')
    ax.grid(axis='y', alpha=0.3, linestyle='--')

    plt.tight_layout()
    plt.savefig(str(output_path), dpi=dpi, bbox_inches='tight', facecolor='white')
    plt.close()
    
    print(f"\nPlot saved to: {output_path}")
    
    return output_path


if __name__ == "__main__":
    dataset_path = "../datasets-np/wl-96-overlap-75-joint-lying-sitting-standing/labels.npy"
    output_path = "./plots/class_distribution.png"
    
    try:
        plot_class_distribution(
            dataset_path=dataset_path,
            output_path=output_path,
            title="Activity Class Distribution",
            figsize=(10, 6),
            dpi=300
        )
        print("\n✓ Class distribution plot created successfully!")
    except FileNotFoundError as e:
        print(f"\n✗ Error: {e}")
        print("\nPlease update the dataset_path to point to a valid dataset file.")
    except Exception as e:
        print(f"\n✗ Unexpected error: {e}")
        import traceback
        traceback.print_exc()
