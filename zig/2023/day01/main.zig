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

pub fn getSpelledNumerals() std.ArrayList([]u8) {
    var n = std.ArrayList([]u8);
    n.append("zero");
    n.append("one");
    n.append("two");
    n.append("three");
    n.append("four");
    n.append("five");
    n.append("six");
    n.append("seven");
    n.append("eight");
    n.append("nine");
    return n;
}

fn getNum(line: []u8) !u32 {
    var out = [2]u16{ 0, 0 };

    for (0..line.len) |i| {
        const ret: ?u32 = try getNumeral(line[0..i], false);
        if (ret != null) {
            out[0] = ret;
            break;
        }
    }

    for (0..line.len) |i| {
        const ret: ?u32 = try getNumeral(line[line.len - i .. line.len], true);
        if (ret != null) {
            out[1] = ret;
            break;
        }
    }

    return out[0] * 10 + out[1];
}

pub fn getNumeral(slice: []u8, reverse: bool) !?u32 {
    if (slice.len == 0) return null;
    const numbers = getSpelledNumerals();
    if (reverse) {
        if (slice[slice.len - 1] >= '0' and slice[slice.len - 1] <= '9') {
            // Try to get regular numerals
            return try std.fmt.parseInt(u32, slice[slice.len - 1 .. slice.len], 10);
        } else {
            // Try to get SPELLED OUT numerals
            for (numbers.items, 0..) |spelled, i| {
                if (slice.len < spelled.len) continue;
                if (std.mem.eql(u8, slice[slice.len - i .. spelled.len], spelled)) {
                    return i;
                }
            }
        }
    } else {
        if (slice[0] >= '0' and slice[0] <= '9') {
            // Try to get regular numerals
            return try std.fmt.parseInt(u32, slice[0..1], 10);
        } else {
            // Try to get SPELLED OUT numerals
            for (numbers.items, 0..) |spelled, i| {
                if (slice.len < spelled.len) continue;
                if (std.mem.eql(u8, slice[0..spelled.len], spelled)) {
                    return i;
                }
            }
        }
    }
    return null;
}

const expect = std.testing.expect;

test "testInput" {
    const input = try egg.readLines(std.heap.page_allocator, "./testInput.txt");
    const expected = [_]u32{ 29, 83, 13, 24, 42, 14, 76 };

    var sum: u32 = 0;
    for (input.items, 0..input.items.len) |line, i| {
        const num: u32 = try getNum(line);
        std.debug.print("expected: {d}, received: {d}\n", .{ expected[i], num });
        try expect(num == expected[i]);
        sum += num;
    }
    try expect(sum == 281);
}
