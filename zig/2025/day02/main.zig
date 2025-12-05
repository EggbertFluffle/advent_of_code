const std = @import("std");

const allocator = std.heap.page_allocator;

pub fn main() !void {
    const input = try read_ranges("input.txt");
    // const input = try read_ranges("test.txt");

    var sum: u64 = 0;
    for(0..input.items.len) |i| {
        const range = input.items[i];
        for(range[0]..(range[1] + 1)) |num| {
            const str = try std.fmt.allocPrint(allocator, "{d}", .{num});
            if(invalid(str)) {
                sum += @intCast(num);
            }
        }
    }
    std.debug.print("sum: {d}\n", .{sum});
}

pub fn invalid(num: []u8) bool {
    for(2..num.len+1) |splits| {
        if(@mod(num.len, splits) != 0) {
            continue;
        }
        const frac = num.len / splits;
        const first = num[0..frac];

        var inv: bool = true;
        for(1..splits) |i| {
            const str = num[(frac * i)..(frac * i + frac)];
            inv = inv and std.mem.eql(u8, first, str);
        }
        if(inv) return true;
    }
    return false;
}

pub fn read_ranges(file_name: []const u8) !std.ArrayList([2]usize) {
    var out: std.ArrayList([2]usize) = try .initCapacity(allocator, 16);
    const file = std.fs.cwd().openFile(file_name, .{ .mode = .read_only }) catch |err| {
        std.debug.print("unable to open file at {s}", .{file_name});
        return err;
    };

    var buf: [1024 * 1024]u8 = undefined;
    var reader = file.reader(&buf);

    while(true) {
        const line = reader.interface.takeDelimiterExclusive('\n') catch { return out; };
        std.debug.print("\"{s}\"\n", .{line});

        var it = std.mem.splitAny(u8, line, "-");

        try out.append(allocator, .{std.fmt.parseInt(usize, it.next().?, 10) catch { return out; }, std.fmt.parseInt(usize, it.next().?, 10) catch { return out; }});
    }
}
