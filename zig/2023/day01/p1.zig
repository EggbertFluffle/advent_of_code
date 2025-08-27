const std = @import("std");

const egg = @import("./EggUtils.zig");

pub fn main() !void {
    const input = try egg.readLines(std.heap.page_allocator, "./input.txt");

    var sum: u32 = 0;
    for (input.items) |line| {
        sum += try getNum(line);
    }

    std.debug.print("sum: {d}\n", .{sum});
}

fn getNum(line: []u8) !u32 {
    var out = [2]u32{ 0, 0 };

    for (line) |char| {
        if (char >= '0' and char <= '9') {
            out[0] = char - 48;
            break;
        }
    }

    for (0..line.len) |i| {
        const char: u8 = line[line.len - i - 1];
        if (char >= '0' and char <= '9') {
            out[1] = char - 48;
            break;
        }
    }

    return out[0] * 10 + out[1];
}

const expect = std.testing.expect;

test "testInput" {
    const input = try egg.readLines(std.heap.page_allocator, "./testInput.txt");
    const expected = [_]u32{ 12, 38, 15, 77 };

    var sum: u32 = 0;
    for (input.items, 0..input.items.len) |line, i| {
        const num: u32 = try getNum(line);
        std.debug.print("expected: {d}, received: {d}\n", .{ expected[i], num });
        try expect(num == expected[i]);
        sum += num;
    }
    try expect(sum == 142);
}
