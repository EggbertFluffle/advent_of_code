const std = @import("std");
const egg = @import("./EggUtils.zig");

pub fn main() !void {
    // const input = try egg.readLines(std.heap.page_allocator, "./testInput.txt");
    const input = try egg.readLines(std.heap.page_allocator, "./input.txt");
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    egg.printAll(input);

    var reports = std.ArrayList([]i32).init(allocator);
    defer reports.deinit();

    var arena = std.heap.ArenaAllocator.init(allocator);
    defer arena.deinit();
    const reportAllocator = arena.allocator();
    for (input.items) |r| {
        var newReport = std.ArrayList(i32).init(reportAllocator);
        defer newReport.deinit();

        var it = std.mem.split(u8, r, " ");
        while (it.next()) |num| {
            try newReport.append(try std.fmt.parseInt(i32, num, 10));
        }
        try reports.append(try newReport.toOwnedSlice());
    }

    var sum: i32 = 0;

    for (reports.items) |r| {
        sum += if (isSafe(r)) 1 else 0;
    }

    std.debug.print("sum: {d}\n", .{sum});
}

pub fn isSafe(report: []i32) bool {
    if (report[0] < report[1]) {
        // Decending
        var i: usize = 0;
        while (i < report.len - 1) {
            const diff: i32 = report[i + 1] - report[i];
            std.debug.print("diff: {d}\n", .{diff});
            if (!(diff >= 1 and diff <= 3)) {
                return false;
            }
            i += 1;
        }
        return true;
    } else {
        // Ascending
        var i: usize = 0;
        while (i < report.len - 1) {
            const diff: i32 = report[i] - report[i + 1];
            std.debug.print("diff: {d}\n", .{diff});
            if (!(diff >= 1 and diff <= 3)) {
                return false;
            }
            i += 1;
        }
        return true;
    }
}
