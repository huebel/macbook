################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/sms/sms_service.cpp 

OBJS += \
./src/sms/sms_service.o 

CPP_DEPS += \
./src/sms/sms_service.d 


# Each subdirectory must supply rules for building sources it contributes
src/sms/%.o: ../src/sms/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DXENO_DARWIN -I../include -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


