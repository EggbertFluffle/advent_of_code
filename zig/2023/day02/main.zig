const std = @import("std");
const egg = @import("./EggUtils.zig");

pub fn main() !void {
    const input = try egg.readLines(std.heap.page_allocator, "./input.txt");

    egg.printAll(input);
}
