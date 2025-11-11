import tensorflow as tf
from tensorflow.keras.models import load_model
from tensorflow.keras.optimizers import Adam


path_to_model = "gmp_wl_24.h5"
model = load_model(path_to_model, compile=False)


model.compile(
    optimizer=Adam(learning_rate=1e-3),
    loss='categorical_crossentropy',
    metrics=['accuracy']
)

new_model_path = "recompiled_gmp_wl_24.h5"
model.save(new_model_path)