import time

# pylint: disable=undefined-variable
Import("env")


# Need to wait for initialization of Serial
def after_upload(source, target, env):
    seconds = 3
    print("Delay after upload for " + str(seconds) + " seconds...")
    time.sleep(seconds)
    print("Done!")


# pylint: disable=undefined-variable
env.AddPostAction("upload", after_upload)
