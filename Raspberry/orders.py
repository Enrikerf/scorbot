from enum import Enum

class CMD_TYPE(Enum):
    NOT_RECOGNIZED  = -1
    ARD             = 0
    AXES            = 1
    LOG             = 2

class CMD_ARD(Enum):
    NOT_RECOGNIZED  = -1
    GET_BRAKE       = 1
    GET_DIR         = 2
    GET_PWM         = 3
    SET_BRAKE       = 4
    SET_DIR         = 5
    SET_PWM         = 6
    GET_BRAKE_PIN   = 7
    GET_DIR_PIN     = 8
    GET_PWM_PIN     = 9
    SET_BRAKE_PIN   = 10
    SET_DIR_PIN     = 11
    SET_PWM_PIN     = 12
    GET_SWITCH      = 13
    SET_SWITCH_PIN  = 14

class CMD_AXES(Enum):
    NOT_RECOGNIZED  = -1

class CMD_LOG(Enum):
    NOT_RECOGNIZED  = -1
    INFO            = 1
    DEBUG           = 2
    ERROR           = 3
    VERBOSE         = 4

class ARG_LOG(Enum):
    NOT_RECOGNIZED  = -1
    ON              = 1
    OFF             = 2
# the position in this list correspond with the number in CMD_TYPE enum
cmds = [CMD_ARD,CMD_AXES,CMD_LOG]