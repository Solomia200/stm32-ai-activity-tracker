"""Module for creating compact CNN architecture diagrams."""

from pathlib import Path
from tensorflow.keras.models import load_model
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.patches import FancyBboxPatch, FancyArrowPatch
import numpy as np


def get_layer_info(layer):
    """Extract layer type and dimensions."""
    layer_type = layer.__class__.__name__
    
    # Get output shape, excluding batch dimension
    try:
        output_shape = layer.output_shape
    except AttributeError:
        # Some layers don't have output_shape, use output.shape instead
        output_shape = layer.output.shape
    
    if isinstance(output_shape, list):
        output_shape = output_shape[0]
    
    # Remove batch dimension
    if len(output_shape) > 1:
        shape = output_shape[1:]
    else:
        shape = output_shape
    
    return layer_type, shape


def get_layer_color(layer_type):
    """Return color for each layer type."""
    color_map = {
        'Conv1D': '#89CFF0',  # Light blue
        'Conv2D': '#89CFF0',
        'MaxPooling1D': '#FF69B4',  # Pink/Magenta
        'MaxPooling2D': '#FF69B4',
        'GlobalMaxPooling1D': '#FF69B4',
        'GlobalMaxPooling2D': '#FF69B4',
        'Flatten': '#FFEB99',  # Yellow
        'Dense': '#90EE90',  # Light green
        'Dropout': '#D3D3D3',  # Light gray
        'BatchNormalization': '#FFB6C1',
        'Activation': '#E6E6FA',
        'InputLayer': '#FFFFFF'
    }
    return color_map.get(layer_type, '#E0E0E0')


def visualize_model_compact(
    model_path: str,
    output_path: str,
    title: str = "Model Architecture",
    figsize: tuple = (16, 6),
    dpi: int = 300
) -> Path:
    """
    Create a compact CNN architecture visualization.
    
    Args:
        model_path: Path to the .h5 model file
        output_path: Path where the diagram will be saved
        title: Title for the diagram
        figsize: Figure size (width, height)
        dpi: Resolution in dots per inch
        
    Returns:
        Path object pointing to the saved diagram
    """
    model_path = Path(model_path)
    output_path = Path(output_path)
    
    if not model_path.exists():
        raise FileNotFoundError(f"Model file not found: {model_path}")
    
    output_path.parent.mkdir(parents=True, exist_ok=True)
    
    print(f"Loading model from: {model_path}")
    model = load_model(str(model_path))
    
    # Extract layer information
    layers_info = []
    for layer in model.layers:
        if layer.__class__.__name__ == 'InputLayer':
            continue
        layer_type, shape = get_layer_info(layer)
        layers_info.append({
            'name': layer.name,
            'type': layer_type,
            'shape': shape,
            'color': get_layer_color(layer_type)
        })
    
    print(f"Creating compact visualization...")
    
    # Create figure
    fig, ax = plt.subplots(figsize=figsize)
    ax.set_xlim(0, 100)
    ax.set_ylim(0, 100)
    ax.axis('off')
    
    # Calculate positions
    num_layers = len(layers_info)
    spacing = 85 / (num_layers + 1)
    x_start = 5
    
    # Draw input
    ax.text(x_start - 2, 50, 'Input', ha='right', va='center', fontsize=10, fontweight='bold')
    
    prev_x = x_start
    
    # Draw layers
    for i, layer_info in enumerate(layers_info):
        x_pos = x_start + (i + 1) * spacing
        
        # Determine layer dimensions for visualization
        if len(layer_info['shape']) >= 2:
            # 2D or higher (e.g., Conv layers)
            height = min(layer_info['shape'][0] / 20, 40)
            width = 3
            depth = min(layer_info['shape'][-1] / 50, 8)
        elif len(layer_info['shape']) == 1:
            # 1D (e.g., Dense layers)
            height = min(layer_info['shape'][0] / 50, 30)
            width = 2
            depth = 0
        else:
            height = 20
            width = 2
            depth = 0
        
        y_center = 50
        
        # Draw 3D-like layer representation
        if depth > 0:
            # Draw multiple rectangles for depth effect
            num_rects = max(3, int(depth))
            for j in range(num_rects):
                offset = j * 0.3
                rect = FancyBboxPatch(
                    (x_pos + offset, y_center - height/2 + offset),
                    width, height,
                    boxstyle="round,pad=0.05",
                    facecolor=layer_info['color'],
                    edgecolor='black',
                    linewidth=1.5,
                    alpha=0.8,
                    zorder=num_rects - j
                )
                ax.add_patch(rect)
        else:
            # Simple rectangle
            rect = FancyBboxPatch(
                (x_pos, y_center - height/2),
                width, height,
                boxstyle="round,pad=0.05",
                facecolor=layer_info['color'],
                edgecolor='black',
                linewidth=1.5,
                alpha=0.8
            )
            ax.add_patch(rect)
        
        # Draw arrow from previous layer
        arrow = FancyArrowPatch(
            (prev_x + 3.5, y_center),
            (x_pos - 0.5, y_center),
            arrowstyle='->,head_width=0.4,head_length=0.8',
            color='black',
            linewidth=1.5,
            zorder=0
        )
        ax.add_patch(arrow)
        
        # Add shape text below
        shape_text = ' × '.join(map(str, layer_info['shape']))
        ax.text(x_pos + width/2, y_center - height/2 - 3,
                shape_text, ha='center', va='top', fontsize=7)
        
        prev_x = x_pos
    
    # Draw output arrow
    arrow = FancyArrowPatch(
        (prev_x + 3.5, 50),
        (95, 50),
        arrowstyle='->,head_width=0.4,head_length=0.8',
        color='black',
        linewidth=1.5,
        zorder=0
    )
    ax.add_patch(arrow)
    
    # Add output text
    if layers_info and 'Dense' in layers_info[-1]['type']:
        output_classes = layers_info[-1]['shape'][-1] if layers_info[-1]['shape'] else 'N'
        ax.text(97, 50, f'{output_classes} classes', ha='left', va='center',
                fontsize=9, fontweight='bold')
    
    # Create legend
    legend_items = []
    layer_types_seen = set()
    
    for layer_info in layers_info:
        layer_type = layer_info['type']
        if layer_type not in layer_types_seen:
            layer_types_seen.add(layer_type)
            legend_items.append(
                mpatches.Patch(color=layer_info['color'], label=layer_type, edgecolor='black')
            )
    
    # Add legend in bottom right
    ax.legend(handles=legend_items, loc='lower right', fontsize=9,
              framealpha=0.9, edgecolor='black')
    
    # Add title
    ax.text(50, 95, title, ha='center', va='top', fontsize=14, fontweight='bold')
    
    plt.tight_layout()
    plt.savefig(str(output_path), dpi=dpi, bbox_inches='tight', facecolor='white')
    plt.close()
    
    print(f"Compact visualization saved to: {output_path}")
    
    # Print model summary
    print("\nModel Summary:")
    print("=" * 60)
    model.summary()
    print("=" * 60)
    
    return output_path


if __name__ == "__main__":
    # Example usage
    model_path = "/home/bohdan/code/poc/human-activity-recognition/stm32-ai-activity-tracker/firmware/resources/trained-models/realworld-dataset/wl-96/wl-96.h5"
    output_path = "./model_diagrams/model_compact.png"
    
    try:
        visualize_model_compact(
            model_path=model_path,
            output_path=output_path,
            title="CNN Activity Recognition Model",
            figsize=(18, 6),
            dpi=300
        )
        print("\n✓ Compact visualization complete!")
    except FileNotFoundError as e:
        print(f"\n✗ Error: {e}")
        print("\nPlease update the model_path to point to a valid .h5 model file.")
    except Exception as e:
        print(f"\n✗ Unexpected error: {e}")
        import traceback
        traceback.print_exc()
