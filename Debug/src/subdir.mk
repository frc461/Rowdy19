################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Autonomous.cpp \
../src/Camera.cpp \
../src/DriveTrain.cpp \
../src/Elevator.cpp \
../src/Intake.cpp \
../src/Robot.cpp \
../src/Sensors.cpp \
../src/SettablePIDOut.cpp \
../src/ShuffleboardPoster.cpp 

OBJS += \
./src/Autonomous.o \
./src/Camera.o \
./src/DriveTrain.o \
./src/Elevator.o \
./src/Intake.o \
./src/Robot.o \
./src/Sensors.o \
./src/SettablePIDOut.o \
./src/ShuffleboardPoster.o 

CPP_DEPS += \
./src/Autonomous.d \
./src/Camera.d \
./src/DriveTrain.d \
./src/Elevator.d \
./src/Intake.d \
./src/Robot.d \
./src/Sensors.d \
./src/SettablePIDOut.d \
./src/ShuffleboardPoster.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-frc-linux-gnueabi-g++ -std=c++1y -I"C:\Users\461/wpilib/cpp/current/include" -I"C:\Users\461\Documents\GitHub\Rowdy19\src" -I"C:\Users\461/wpilib/user/cpp/include" -O0 -Og -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


