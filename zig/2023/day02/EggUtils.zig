const std = @import("std");

pub fn readLines(allocator: std.mem.Allocator, filepath: []const u8) !std.ArrayList([]u8) { // Open the file
    const file = try std.fs.cwd().openFile(filepath, .{});
    defer file.close();

    // Create a buffered reader
    var buf_reader = std.io.bufferedReader(file.reader());
    var in_stream = buf_reader.reader();

    // Create an ArrayList to store the lines
    var lines = std.ArrayList([]u8).init(allocator);
    errdefer {
        for (lines.items) |line| {
            allocator.free(line);
        }
        lines.deinit();
    }

    // Read lines until EOF
    while (true) {
        // Read a line from the file
        const line = in_stream.readUntilDelimiterAlloc(allocator, '\n', 1024 * 1024) catch |err| switch (err) {
            error.EndOfStream => break,
            else => return err,
        };

        try lines.append(line);
    }

    return lines;
}

pub fn printAll(lines: std.ArrayList([]u8)) void {
    var i: usize = 0;
    while (i < lines.items.len) : (i += 1) {
        std.debug.print("{s}\n", .{lines.items[i]});
    }
}
