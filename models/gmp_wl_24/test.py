import tensorflow as tf
model = tf.keras.models.load_model("./gmp_wl_24.h5", compile=False)
model.summary()