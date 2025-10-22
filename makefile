.PHONY: all assembler processor clean assembler_only processor_only run-assembler run-processor run-VP

all: assembler processor

assembler: 
	@echo "Building Assembler...."
	$(MAKE) -C Assembler -f makefile_Assembler


processor:
	@echo "Building Processor...."
	$(MAKE) -C Processor -f makefile_Processor 
clean:
	$(MAKE) -C Assembler -f makefile_Assembler clean
	$(MAKE) -C Processor -f makefile_Processor clean

run-assembler: assembler
	cd Assembler && assembler.exe

run-processor: processor
	cd Processor && processor.exe

run-VP: assembler processor
	@echo "=== Running Virtual Processor ==="
	cd Assembler && assembler.exe
	@echo "---"
	cd Processor && processor.exe