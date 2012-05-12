################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Digital.cpp \
../EZ_SDK.cpp \
../HC_SR04.cpp \
../Servo.cpp \
../ezb_conn.cpp 

OBJS += \
./Digital.o \
./EZ_SDK.o \
./HC_SR04.o \
./Servo.o \
./ezb_conn.o 

CPP_DEPS += \
./Digital.d \
./EZ_SDK.d \
./HC_SR04.d \
./Servo.d \
./ezb_conn.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -fpermissive -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


