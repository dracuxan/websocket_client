.PHONY: build clean test

all: build

build:
	@echo "Generating Ninja..."
	@gn gen out

	@echo "Building Project..."
	@ninja -C out

clean:
	@echo "Cleaning build artifacts..."
	@rm -rf out

run:
	./out/main
