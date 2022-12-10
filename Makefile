SESSION=$(shell cat session)

clean:
	rm -rf ./build

build/%: src/%.cpp
	mkdir -p build && \
	c++ -std=c++20 -o $@ $^

data/%:
	curl -o $@ "https://adventofcode.com/2022/day/$*/input" --cookie ${SESSION}
