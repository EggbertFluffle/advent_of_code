const std = @import("std");

const allocator = std.heap.page_allocator;

// const grid_size: usize = 139;
const grid_size: usize = 139;

pub fn main() !void {
    const input = try read_lines("input.txt");
    // const input = try read_lines("test.txt");

    var grid: [grid_size][grid_size]bool = input;

    var sum: i32 = 0;
    var removed: i32 = 1;
    while(removed != 0) {
        removed = 0;
        grid = next_grid(grid, &removed);
        sum += removed;
    }  

    // for(0..grid_size) |x| {
    //     for(0..grid_size) |y| {
    //         std.debug.print("{s}", .{if (grid[x][y]) "#" else " "});
    //     }
    //     std.debug.print("\n", .{});
    // }

    std.debug.print("sum: {d}\n", .{sum});
}

pub fn next_grid(grid: [grid_size][grid_size]bool, removed: *i32) [grid_size][grid_size]bool {
    var next: [grid_size][grid_size]bool = grid;

    for(0..grid_size) |x| {
        for(0..grid_size) |y| {
            if(grid[x][y] and count_neighbors(&grid, @intCast(x), @intCast(y)) < 4) {
                removed.* += 1;
                next[x][y] = false;
            }
        }
    }

    return next;
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

pub fn copy_grid(grid: *[grid_size][grid_size]bool) [grid_size][grid_size]bool {
    var out: [grid_size][grid_size]bool = undefined;

    for(0..grid_size) |x| {
        std.mem.copyForwards(bool, &out[x], &grid[x]);
    }

    return out;
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
