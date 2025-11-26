import tensorflow as tf
import tensorflow.keras.layers as layers


def get_model(input_shape: tuple[int],
            num_classes: int,
            dropout: float = 0.35):
    inputs = layers.Input(shape=input_shape)

    x = layers.BatchNormalization()(inputs)
    x = layers.Conv1D(filters=32, kernel_size=5, activation='relu',
                      kernel_initializer='he_uniform')(x)

    x= layers.MaxPooling1D(pool_size=2)(x)

    x = layers.BatchNormalization()(x)
    x = layers.Conv1D(filters=64, kernel_size=5, activation='relu',
                      kernel_initializer='he_uniform')(x)

    x = layers.BatchNormalization()(x)
    x = layers.Conv1D(filters=96, kernel_size=3, activation='relu',
                      kernel_initializer='he_uniform')(x)

    x = layers.GlobalAveragePooling1D()(x)


    if dropout:
        x = layers.Dropout(dropout)(x)

    x = layers.BatchNormalization()(x)
    x = layers.Dense(64, activation='relu', kernel_initializer="he_uniform")(x)
    x = layers.BatchNormalization()(x)
    
    x = layers.Dense(num_classes)(x)
    outputs = layers.Activation('softmax')(x)

    model = tf.keras.Model(inputs=inputs, outputs=[outputs], name="our_model_v2")
    return model
