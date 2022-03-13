#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    string roleName;
    vector<string> subRoles;
    string reportTo;

    TreeNode(string rName, string parent)
    {
        roleName = rName;
        reportTo = parent;
    }
};

TreeNode *root = NULL;
unordered_map<string, TreeNode *> roleNodes;
unordered_map<string, vector<string>> roleUsers;
unordered_map<string, string> userRole;

/*--------------------Support Functions ------------*/

void addSubRole()
{
    string subRole, reportTo;

    cout << "Enter Sub Role Name : ";
    cin >> subRole;

    cout << "Enter reporting role name : ";
    cin >> reportTo;

    TreeNode *subRoleNode = new TreeNode(subRole, reportTo);
    roleNodes[subRole] = subRoleNode;

    roleNodes[reportTo]->subRoles.push_back(subRole);
}

void displayRoles()
{
    queue<TreeNode *> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode *curr = q.front();
        q.pop();

        cout << curr->roleName << ", ";

        for (int i = 0; i < curr->subRoles.size(); i++)
        {
            q.push(roleNodes[curr->subRoles[i]]);
        }
    }
    cout << endl;
}

void deleteRole()
{
    string delRole, transferTo;
    cout << "Enter the role to be delete : ";
    cin >> delRole;

    cout << "Enter the role to be transfered : ";
    cin >> transferTo;

    TreeNode *delRoleNode = roleNodes[delRole];
    TreeNode *trnsRoleNode = roleNodes[transferTo];

    for (int i = 0; i < delRoleNode->subRoles.size(); i++)
    {
        string subRoleName = delRoleNode->subRoles[i];
        roleNodes[subRoleName]->reportTo = transferTo;

        trnsRoleNode->subRoles.push_back(subRoleName);
    }

    string prntName = delRoleNode->reportTo;
    TreeNode *prntNode = roleNodes[prntName];

    prntNode->subRoles.erase(find(prntNode->subRoles.begin(), prntNode->subRoles.end(), delRole));

    for (auto &user : roleUsers[delRole])
    {
        userRole.erase(user);
    }

    roleUsers.erase(delRole);
}

void addUser()
{
    string userName, role;
    cout << "Enter User Name : ";
    cin >> userName;

    cout << "Enter role : ";
    cin >> role;

    roleUsers[role].push_back(userName);
    userRole[userName] = role;
}

void displayUsers()
{
    for (auto it : roleUsers)
    {
        string role = it.first;
        for (auto &user : it.second)
        {
            cout << user << " - " << role << endl;
        }
    }
}

void displayUserAndSub()
{
    /*---------Implement-----*/
}

void deleteUser()
{
    string user;
    cout << "Enter username to be deleted : ";
    cin >> user;

    string role = userRole[user];

    roleUsers[role].erase(find(roleUsers[role].begin(), roleUsers[role].end(), user));
    userRole.erase(user);
}

void numberOfUserFromTop()
{
    string user;
    cout << "Enter user name : ";
    cin >> user;

    string role = userRole[user];

    int cnt = 0;

    TreeNode *curr = roleNodes[role];
    curr = roleNodes[curr->reportTo];

    while (curr != root)
    {
        cnt += roleUsers[curr->roleName].size();
        curr = roleNodes[curr->reportTo];
    }

    cnt += roleUsers[curr->roleName].size();

    cout << "Number of users from top : " << cnt << endl;
}

int getHeightHelper(TreeNode *root)
{
    if (!root)
        return 0;

    int mx = 0;
    for (int i = 0; i < root->subRoles.size(); i++)
    {
        mx = max(mx, getHeightHelper(roleNodes[root->subRoles[i]]));
    }
    return 1 + mx;
}

void getHeight()
{
    int mx = INT_MIN;
    for (int i = 0; i < root->subRoles.size(); i++)
    {
        mx = max(mx, getHeightHelper(roleNodes[root->subRoles[i]]));
    }
    cout << 1 + mx << endl;
}

void commonBoss()
{
}

/*---------------------Support Functions Ends---------*/

int main()
{
    string rootRoleName;
    cout << "\nEnter root role name : ";
    cin >> rootRoleName;
    cout << endl;

    TreeNode *rootNode = new TreeNode(rootRoleName, "NULL");
    root = rootNode;
    roleNodes[rootRoleName] = rootNode;

    while (true)
    {
        cout << "Operations :\n";
        cout << " 1. Add Sub Role.\n";
        cout << " 2. Display Roles.\n";
        cout << " 3. Delete Role.\n";
        cout << " 4. Add User.\n";
        cout << " 5. Display Users.\n";
        cout << " 6. Display Users and Sub Users.\n";
        cout << " 7. Delete User.\n";
        cout << " 8. Number of Users from top.\n";
        cout << " 9. Height of Role Hierachy.\n";
        cout << " 10. Common boss of users.\n";

        cout << "\nOperation to be performed : ";
        int ch = 0;
        cin >> ch;

        switch (ch)
        {
        case 1:
            addSubRole();
            break;

        case 2:
            displayRoles();
            break;

        case 3:
            deleteRole();
            break;

        case 4:
            addUser();
            break;

        case 5:
            displayUsers();
            break;

        case 6:
            displayUserAndSub();
            break;

        case 7:
            deleteUser();
            break;

        case 8:
            numberOfUserFromTop();
            break;

        case 9:
            getHeight();
            break;

        case 10:
            commonBoss();
            break;

        default:
            break;
        }
    }
}