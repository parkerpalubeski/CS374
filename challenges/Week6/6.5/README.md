When you kill -USR1 several times, only one signal seems to come through and get handled. Why is that?

When the signal is blocked,  any additional signals are resolved/discarded rather than queueing to be sent. That's why only one signal goes through. Even though multiple signals are sent, behind the scenes the OS is discarding any signals that are sent after the first blocked signal.