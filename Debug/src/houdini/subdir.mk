################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_UPPER_SRCS += \
../src/houdini/SOP_Quarks.C 

CPP_SRCS += \
../src/houdini/AttribManager.cpp \
../src/houdini/HQAdapter.cpp 

O_SRCS += \
../src/houdini/SOP_Quarks.o 

OBJS += \
./src/houdini/AttribManager.o \
./src/houdini/HQAdapter.o \
./src/houdini/SOP_Quarks.o 

C_UPPER_DEPS += \
./src/houdini/SOP_Quarks.d 

CPP_DEPS += \
./src/houdini/AttribManager.d \
./src/houdini/HQAdapter.d 


# Each subdirectory must supply rules for building sources it contributes
src/houdini/%.o: ../src/houdini/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/houdini/%.o: ../src/houdini/%.C
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


