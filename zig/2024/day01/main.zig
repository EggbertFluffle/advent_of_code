const std = @import("std");
const egg = @import("./EggUtils.zig");

pub fn main() !void {
    const input = try egg.readLines(std.heap.page_allocator, "./input.txt");
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    var rightList = try allocator.alloc(i32, input.items.len);
    defer allocator.free(rightList);

    var leftList = try allocator.alloc(i32, input.items.len);
    defer allocator.free(leftList);

    for (input.items, 0..) |line, i| {
        const pos = std.mem.indexOf(u8, line, " ") orelse 0;

        rightList[i] = try std.fmt.parseInt(i32, line[0..pos], 10);
        leftList[i] = try std.fmt.parseInt(i32, line[pos + 1 .. line.len], 10);
        std.debug.print("{d}\n", .{rightList[i]});
    }

    var sum: i64 = 0;
    for (leftList) |l| {
        sum += l * count(rightList, l);
    }

    std.debug.print("sum: {d}\n", .{sum});
}

pub fn count(haystack: []i32, needle: i32) i32 {
    var sum: i32 = 0;
    for (haystack) |n| {
        sum += if (n == needle) 1 else 0;
    }
    return sum;
}
