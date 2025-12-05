const std = @import("std");

const allocator = std.heap.page_allocator;

const Range = @Vector(2, u64);

pub fn main() !void {
    const ranges = try read_ranges("input_ranges.txt");
    const ids = try read_ids("input_ids.txt");
    // const ranges = try read_ranges("test_ranges.txt");
    // const ids = try read_ids("test_ids.txt");

    var sum: u64 = 0;
    for(ids.items) |id| {
        sum += blk: {
            for(ranges.items) |range| {
                if(id >= range[0] and id <= range[1]) {
                    break :blk 1;
                }
            }
            break :blk 0;
        };
    }
    std.debug.print("{d}\n", .{sum});
}

pub fn read_ranges(file_name: []const u8) !std.ArrayList(Range) {
    var out: std.ArrayList(Range) = try .initCapacity(allocator, 100);
    const file = std.fs.cwd().openFile(file_name, .{ .mode = .read_only }) catch |err| {
        std.debug.print("unable to open file at {s}", .{file_name});
        return err;
    };

    var buf: [1024 * 1024]u8 = undefined;
    var reader = file.reader(&buf);

    while(true) {
        const line = reader.interface.takeDelimiterExclusive('\n') catch { return out; };

        const split = std.mem.indexOf(u8, line, "-");
        if(split == null) continue;

        try out.append(allocator, Range{
            try std.fmt.parseInt(u64, line[0..split.?], 10),
            try std.fmt.parseInt(u64, line[split.? + 1..line.len], 10),
        });
    }
    return out;
}

pub fn read_ids(file_name: []const u8) !std.ArrayList(u64) {
    var out: std.ArrayList(u64) = try .initCapacity(allocator, 100);
    const file = std.fs.cwd().openFile(file_name, .{ .mode = .read_only }) catch |err| {
        std.debug.print("unable to open file at {s}", .{file_name});
        return err;
    };

    var buf: [1024 * 1024]u8 = undefined;
    var reader = file.reader(&buf);

    while(true) {
        const line = reader.interface.takeDelimiterExclusive('\n') catch { return out; };

        try out.append(allocator, try std.fmt.parseInt(u64, line, 10));
    }
    return out;
}
