################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DriveTrain.cpp \
../src/Robot.cpp \
../src/ShuffleboardPoster.cpp 

OBJS += \
./src/DriveTrain.o \
./src/Robot.o \
./src/ShuffleboardPoster.o 

CPP_DEPS += \
./src/DriveTrain.d \
./src/Robot.d \
./src/ShuffleboardPoster.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-frc-linux-gnueabi-g++ -std=c++1y -I"/Users/hank/wpilib/cpp/current/include" -I"/Users/hank/eclipse-workspace/Rowdy19/src" -I"/Users/hank/wpilib/user/cpp/include" -O0 -Og -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


