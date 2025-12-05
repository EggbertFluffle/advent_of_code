const std = @import("std");

const allocator = std.heap.page_allocator;

// const grid_size: usize = 139;
const grid_size: usize = 139;

pub fn main() !void {
    const input = try read_lines("input.txt");
    // const input = try read_lines("test.txt");

    var sum: i32 = 0;
    for(0..grid_size) |x| {
        for(0..grid_size) |y| {
            if(input[x][y]) {
                sum += if (count_neighbors(&input, @intCast(x), @intCast(y)) < 4) 1 else 0;
            }
        }
    }  
    std.debug.print("sum: {d}\n", .{sum});
}

pub fn in_bounds(x: i32, y: i32) bool {
    return x >= 0 and x < grid_size and y >= 0 and y < grid_size;
}

pub fn count_neighbors(grid: *const [grid_size][grid_size]bool, x: i32, y: i32) i32 {
    var count: i32 = 0;
    const offsets = [_][2]i32{
        .{-1, -1}, .{-1, 0}, .{-1, 1},
        .{ 0, -1},           .{ 0, 1},
        .{ 1, -1}, .{ 1, 0}, .{ 1, 1},
    };
    for (offsets) |offset| {
        const xoff: i32 = x + offset[0];
        const yoff: i32 = y + offset[1];
        if(!in_bounds(xoff, yoff)) continue;

        count += if (grid[@intCast(xoff)][@intCast(yoff)]) 1 else 0;
    }
    return count;
}

pub fn read_lines(file_name: []const u8) ![grid_size][grid_size]bool {
    var out: [grid_size][grid_size]bool = undefined;
    const file = std.fs.cwd().openFile(file_name, .{ .mode = .read_only }) catch |err| {
        std.debug.print("unable to open file at {s}", .{file_name});
        return err;
    };

    var buf: [1024 * 1024]u8 = undefined;
    var reader = file.reader(&buf);

    for(0..grid_size) |y| {
        const line = reader.interface.takeDelimiterExclusive('\n') catch { return out; };
        for(0..grid_size) |x| {
            out[x][y] = line[x] == '@';
        }
    }
    return out;
}
