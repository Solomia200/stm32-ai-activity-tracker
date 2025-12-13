"""Module for visualizing neural network model architecture using visualkeras."""

from pathlib import Path
from tensorflow.keras.models import load_model
import visualkeras


def visualize_model_layered(
    model_path: str,
    output_path: str,
    legend: bool = True,
    scale_xy: float = 1.0,
    scale_z: float = 0.1,
    max_xy: int = 300,
    max_z: int = 1000
) -> Path:
    """
    Create a layered visualization of the model using visualkeras.
    
    This creates a beautiful 3D-style representation showing the model's layers
    as stacked blocks with sizes proportional to their dimensions.
    
    Args:
        model_path: Path to the .h5 model file
        output_path: Path where the diagram will be saved (e.g., 'model_layered.png')
        legend: Whether to show the legend
        scale_xy: Scaling factor for x and y dimensions
        scale_z: Scaling factor for z dimension (depth)
        max_xy: Maximum size for x and y dimensions
        max_z: Maximum size for z dimension
        
    Returns:
        Path object pointing to the saved diagram
    """
    model_path = Path(model_path)
    output_path = Path(output_path)
    
    if not model_path.exists():
        raise FileNotFoundError(f"Model file not found: {model_path}")
    
    # Create output directory if it doesn't exist
    output_path.parent.mkdir(parents=True, exist_ok=True)
    
    print(f"Loading model from: {model_path}")
    model = load_model(str(model_path))
    
    print(f"Generating layered visualization with visualkeras...")
    
    # visualkeras.layered_view(
    #     model,
    #     legend=legend,
    #     scale_xy=scale_xy,
    #     scale_z=scale_z,
    #     max_xy=max_xy,
    #     max_z=max_z,
    #     spacing=20,
    #     to_file=str(output_path)
    # )
    visualkeras.layered_view(model)

    print(f"Layered visualization saved to: {output_path}")
    
    # Print model summary
    print("\nModel Summary:")
    print("=" * 60)
    model.summary()
    print("=" * 60)
    
    return output_path


if __name__ == "__main__":
    # Example usage
    model_path = "/home/bohdan/code/poc/human-activity-recognition/stm32-ai-activity-tracker/firmware/resources/trained-models/realworld-dataset/wl-96/wl-96.h5"
    output_path = "./model_diagrams/model_layered.png"
    
    try:
        visualize_model_layered(
            model_path=model_path,
            output_path=output_path,
            legend=True,
            scale_xy=1.0,
            scale_z=0.1
        )
        print("\n✓ Layered visualization complete!")
    except FileNotFoundError as e:
        print(f"\n✗ Error: {e}")
        print("\nPlease update the model_path to point to a valid .h5 model file.")
    except Exception as e:
        print(f"\n✗ Unexpected error: {e}")
