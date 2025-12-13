"""Module for visualizing neural network model architecture."""

from pathlib import Path
from tensorflow.keras.models import load_model
from tensorflow.keras.utils import plot_model


def visualize_model(
    model_path: str,
    output_path: str,
    show_shapes: bool = True,
    show_layer_names: bool = True,
    show_layer_activations: bool = False,
    rankdir: str = 'TB',
    expand_nested: bool = True,
    dpi: int = 96
) -> Path:
    """
    Load a Keras model and save its architecture diagram.
    
    Args:
        model_path: Path to the .h5 model file
        output_path: Path where the diagram will be saved (e.g., 'model.png')
        show_shapes: Whether to display shape information
        show_layer_names: Whether to display layer names
        show_layer_activations: Whether to display layer activations
        rankdir: Direction of the graph: 'TB' (top-bottom) or 'LR' (left-right)
        expand_nested: Whether to expand nested models
        dpi: Dots per inch for the output image
        
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
    
    print(f"Generating model diagram...")
    plot_model(
        model,
        to_file=str(output_path),
        show_shapes=show_shapes,
        show_layer_names=show_layer_names,
        show_layer_activations=show_layer_activations,
        rankdir=rankdir,
        expand_nested=expand_nested,
        dpi=dpi
    )
    
    print(f"Model diagram saved to: {output_path}")
    
    # Print model summary
    print("\nModel Summary:")
    print("=" * 60)
    model.summary()
    print("=" * 60)
    
    return output_path


if __name__ == "__main__":
    # Example usage
    model_path = "/home/bohdan/code/poc/human-activity-recognition/stm32-ai-activity-tracker/firmware/resources/trained-models/realworld-dataset/wl-96/wl-96.h5"
    output_path = "./model_diagrams/model_architecture.png"
    
    try:
        visualize_model(
            model_path=model_path,
            output_path=output_path,
            show_shapes=True,
            show_layer_names=True,
            rankdir='TB',
            dpi=150
        )
        print("\n✓ Visualization complete!")
    except FileNotFoundError as e:
        print(f"\n✗ Error: {e}")
        print("\nPlease update the model_path to point to a valid .h5 model file.")
    except Exception as e:
        print(f"\n✗ Unexpected error: {e}")
