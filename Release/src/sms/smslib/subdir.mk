################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/sms/smslib/smslib.m

OBJS += \
./src/sms/smslib/smslib.o 

CPP_DEPS += \
./src/sms/smslib/smslib.d 


# Each subdirectory must supply rules for building sources it contributes
src/sms/smslib/%.o: ../src/sms/smslib/%.m
	@echo 'Building file: $<'
	@echo 'Invoking: Clang Obj-C Compiler'
	clang -DXENO_DARWIN -Os -g0 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

