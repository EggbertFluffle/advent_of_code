const std = @import("std");

const allocator = std.heap.page_allocator;

pub fn main() !void {
    const input = try read_lines("input.txt");
    // const input = try read_lines("test.txt");

    var sum: i32 = 0;
    var dial: i32 = 50;
    for(0..input.items.len) |i| {
        const line = input.items[i];

        const digit: usize = try std.fmt.parseInt(usize, line[1..line.len], 10);
        if (line[0] == 'R') {
            for(0..digit) |_| {
                dial += 1;

                if(dial > 99) dial = 0;

                if(dial == 0) {
                    sum += 1;
                }
            }
        } else {
            // Left
            for(0..digit) |_| {
                dial -= 1;

                if(dial < 0) dial = 99;

                if(dial == 0) {
                    sum += 1;
                }
            }
        }

    }
    std.debug.print("sum: {d}\n", .{sum});
}

pub fn read_lines(file_name: []const u8) !std.ArrayList([]u8) {
    var out: std.ArrayList([]u8) = try .initCapacity(allocator, 16);
    const file = std.fs.cwd().openFile(file_name, .{ .mode = .read_only }) catch |err| {
        std.debug.print("unable to open file at {s}", .{file_name});
        return err;
    };

    var buf: [1024 * 1024]u8 = undefined;
    var reader = file.reader(&buf);

    while(true) {
        try out.append(allocator, reader.interface.takeDelimiterExclusive('\n') catch {
            return out;
        });
    }
}
