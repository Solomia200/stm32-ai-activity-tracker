import tensorflow as tf
import tensorflow.keras.layers as layers


def get_model(input_shape: tuple[int] = (24, 3, 1),
            num_classes: int = 4,
            dropout: float = 0.5):
    inputs = layers.Input(shape=input_shape)

    x = layers.BatchNormalization()(inputs)
    x = layers.Conv2D(32, kernel_size=(5, 1), activation='relu', padding='valid',
                      kernel_initializer='glorot_uniform')(x)

    x = layers.BatchNormalization()(x)
    x = layers.Conv2D(32, kernel_size=(5, 1), activation='relu',
                      kernel_initializer='glorot_uniform')(x)

    x = layers.BatchNormalization()(x)
    x = layers.Conv2D(64, kernel_size=(3, 1), activation='relu',
                      kernel_initializer='glorot_uniform')(x)

    x = layers.GlobalAveragePooling2D()(x)
    if dropout:
        x = layers.Dropout(dropout)(x)
    x = layers.Dense(64, activation='relu')(x)
    x = layers.BatchNormalization()(x)
    x = layers.Dense(num_classes)(x)
    outputs = layers.Activation('softmax')(x)

    model = tf.keras.Model(inputs=inputs, outputs=[outputs], name="our_model")
    return model
