const std = @import("std");

const allocator = std.heap.page_allocator;

const Range = @Vector(2, u64);

const RNode = struct {
    range: Range,
    node: std.DoublyLinkedList.Node = .{}
};

pub fn main() !void {
    const ranges = try read_ranges("input_ranges.txt");
    // const ranges = try read_ranges("test_ranges.txt");

    var melt: std.DoublyLinkedList = .{};

    var last: RNode = .{ .range = Range{std.math.maxInt(u64), std.math.maxInt(u64)} };
    var first: RNode = .{ .range = Range{0, 0} };
    melt.prepend(&last.node);
    melt.prepend(&first.node);

    for (ranges.items) |range| {
        try merge(range, &melt);
    }

    melt.remove(&first.node);
    melt.remove(&last.node);

    var sum: u64 = 0;
    var it = melt.first;
    while (it) |node| : (it = node.next) {
        const r_node: *RNode = @alignCast(@fieldParentPtr("node", node));
        sum += r_node.range[1] - r_node.range[0] + 1;
    }
    std.debug.print("sum: {d}\n", .{sum});
}

pub fn merge(range: Range, melt: *std.DoublyLinkedList) !void {
    var it = melt.first;
    var primed = false;
    while (it) |node| : (it = node.next) {
        const r_node: *RNode = @alignCast(@fieldParentPtr("node", node));
        const current = r_node.range;

        if(collide(range, current)) {
            std.DoublyLinkedList.remove(melt, &r_node.node);
            try merge(Range{@min(current[0], range[0]), @max(current[1], range[1])}, melt);
            return;
        } else if(current[1] < range[0]) {
            primed = true;
        } else if (primed and range[1] < current[0]) {
            const new_node = try allocator.create(RNode);
            new_node.range = range;
            std.DoublyLinkedList.insertBefore(melt, &r_node.node, &new_node.node);
            return;
        }
    }
}

pub fn collide(r1: Range, r2: Range) bool {
    return (r1[0] <= r2[0] and r1[1] >= r2[0]) or (r2[0] <= r1[0] and r2[1] >= r1[0]);
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
