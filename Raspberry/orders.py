from enum import Enum

class CMD_TYPE(Enum):
    NOT_RECOGNIZED  = -1
    ARD             = 0
    AXES            = 1
    LOG             = 2

class CMD_ARD(Enum):
    NOT_RECOGNIZED  = -1
    GET_BRAKE       = 0
    GET_DIR         = 1
    GET_PWM         = 2
    SET_BRAKE       = 3
    SET_DIR         = 4
    SET_PWM         = 5
    GET_BRAKE_PIN   = 6
    GET_DIR_PIN     = 7
    GET_PWM_PIN     = 8
    SET_BRAKE_PIN   = 9
    SET_DIR_PIN     = 10
    SET_PWM_PIN     = 11
    GET_SWITCH      = 12
    SET_SWITCH_PIN  = 13

class CMD_AXES(Enum):
    NOT_RECOGNIZED  = -1
    GET_BRAKE       = 0
    GET_DIR         = 1
    GET_PWM         = 2
    SET_BRAKE       = 3
    SET_DIR         = 4
    SET_PWM         = 5
    GET_BRAKE_PIN   = 6
    GET_DIR_PIN     = 7
    GET_PWM_PIN     = 8
    SET_BRAKE_PIN   = 9
    SET_DIR_PIN     = 10
    SET_PWM_PIN     = 11
    GET_SWITCH      = 12
    SET_SWITCH_PIN  = 13

class CMD_LOG(Enum):
    NOT_RECOGNIZED  = -1
    INFO            = 0
    DEBUG           = 1
    ERROR           = 2
    VERBOSE         = 3

class ARG_LOG(Enum):
    NOT_RECOGNIZED  = -1
    ON              = 0
    OFF             = 1
# the position in this list correspond with the number in CMD_TYPE enum
cmds = [CMD_ARD,CMD_AXES,CMD_LOG]
