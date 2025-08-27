const std = @import("std");

pub fn split_string(string: []const u8, delimiter: []const u8) std.ArrayList([]const u8) {
    var iterator = std.mem.splitSequence(u8, string, delimiter);
    var splits: std.ArrayList([]const u8) = std.ArrayList([]const u8).init(std.heap.page_allocator);

    // First item in a sequence SPLIT is guaranteed
    splits.append(iterator.first()) catch {
        return splits;
    };

    var curr = iterator.next();
    while (curr != null) : (curr = iterator.next()) {
        splits.append(curr.?) catch {
            return splits;
        };
    }

    return splits;
}

pub fn tokenize_string(string: []const u8, delimiter: []const u8) std.ArrayList([]const u8) {
    var iterator = std.mem.tokenizeSequence(u8, string, delimiter);
    var splits: std.ArrayList([]const u8) = std.ArrayList([]const u8).init(std.heap.page_allocator);

    var curr = iterator.next();
    while (curr != null) : (curr = iterator.next()) {
        splits.append(curr.?) catch {
            return splits;
        };
    }

    return splits;
}

pub fn read_file(file_path: []const u8) ![]u8 {
    const file = try std.fs.cwd().openFile(file_path, .{});
    defer file.close();

    return try file.readToEndAlloc(std.heap.page_allocator, 1_000_000_000);
}

pub fn read_file_lines(file_path: []const u8) !std.ArrayList([]const u8) {
    return tokenize_string(try read_file(file_path), "\n");
}

pub fn print_all(T: type, arr: std.ArrayList(T)) void {
    for (arr.items) |el| {
        std.debug.print("{any}\n", .{el});
    }
}
