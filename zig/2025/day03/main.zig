const std = @import("std");

const allocator = std.heap.page_allocator;

const line_size: usize = 100;
const num_size: usize = 12;

pub fn main() !void {
    const input = try read_lines("input.txt");
    // const input = try read_lines("test.txt");

    var sum: u64 = 0;
    for(input.items) |line| {
        const num = try get_line_joltage(line);
        sum += num;
    }  
    std.debug.print("sum: {d}\n", .{sum});
}

pub fn get_line_joltage(line: [line_size]u64) !u64 {
    var indexes: std.ArrayList(usize) = try .initCapacity(allocator, line_size);

    try get_joltage(&line, 0, &indexes);

    var sum: u64 = 0;
    std.mem.sort(usize, indexes.items, {}, comptime std.sort.asc(usize));

    for(indexes.items) |i| {
        sum *= 10;
        sum += line[i];
    }

    return sum;
}

pub fn get_joltage(nums: []const u64, offset: usize, indexes: *std.ArrayList(usize)) !void {
    if(nums.len == 0) return;
    
    const pos = std.mem.indexOfMax(u64, nums);
    try indexes.append(allocator, pos + offset);

    if (indexes.items.len != num_size) try get_joltage(nums[pos + 1..nums.len], offset + pos + 1, indexes);
    if (indexes.items.len != num_size) try get_joltage(nums[0..pos], offset, indexes);
}

pub fn read_lines(file_name: []const u8) !std.ArrayList([line_size]u64) {
    var out: std.ArrayList([line_size]u64) = try .initCapacity(allocator, 16);
    const file = std.fs.cwd().openFile(file_name, .{ .mode = .read_only }) catch |err| {
        std.debug.print("unable to open file at {s}", .{file_name});
        return err;
    };

    var buf: [1024 * 1024]u8 = undefined;
    var reader = file.reader(&buf);

    while(true) {
        const line = reader.interface.takeDelimiterExclusive('\n') catch { return out; };
        var nums: [line_size]u64 = undefined;

        for(0..line.len) |i| {
            nums[i] = try std.fmt.parseInt(u64, line[i..i+1], 10);
        }

        try out.append(allocator, nums);
    }
}
