cpp_files = Dir["**/*.cpp"]

cpp_files.each do |cpp_file|
	f = File.open(cpp_file, "r+")
	lines = f.readlines
	f.close

	lines = ["#include \"stdafx.h\"\n\n"] + lines

	output = File.new(cpp_file, "w")
	lines.each { |line| output.write line }
	output.close
end

